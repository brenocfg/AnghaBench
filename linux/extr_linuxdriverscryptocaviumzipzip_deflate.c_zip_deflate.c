#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ totalbyteswritten; int /*<<< orphan*/  crc32; int /*<<< orphan*/  adler32; int /*<<< orphan*/  compcode; } ;
union zip_zres_s {TYPE_2__ s; } ;
typedef  union zip_inst_s {int dummy; } zip_inst_s ;
typedef  int /*<<< orphan*/  u32 ;
struct zip_state {union zip_zres_s result; union zip_inst_s zip_cmd; } ;
struct zip_operation {scalar_t__ input_len; int format; scalar_t__ output_len; int /*<<< orphan*/  csum; int /*<<< orphan*/  compcode; } ;
struct TYPE_3__ {int /*<<< orphan*/  comp_out_bytes; int /*<<< orphan*/  comp_req_complete; int /*<<< orphan*/  comp_req_submit; int /*<<< orphan*/  comp_in_bytes; } ;
struct zip_device {TYPE_1__ stats; } ;

/* Variables and functions */
#define  GZIP_FORMAT 134 
#define  LZS_FORMAT 133 
#define  RAW_FORMAT 132 
#define  ZIP_CMD_DTRUNC 131 
#define  ZIP_CMD_NOTDONE 130 
#define  ZIP_CMD_SUCCESS 129 
 int ZIP_ERROR ; 
#define  ZLIB_FORMAT 128 
 int /*<<< orphan*/  atomic64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_zip_command (struct zip_operation*,struct zip_state*,union zip_inst_s*) ; 
 int /*<<< orphan*/  zip_dbg (char*,...) ; 
 int /*<<< orphan*/  zip_err (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  zip_load_instr (union zip_inst_s*,struct zip_device*) ; 
 int /*<<< orphan*/  zip_poll_result (union zip_zres_s*) ; 
 int /*<<< orphan*/  zip_update_cmd_bufs (struct zip_device*,int /*<<< orphan*/ ) ; 

int zip_deflate(struct zip_operation *zip_ops, struct zip_state *s,
		struct zip_device *zip_dev)
{
	union zip_inst_s *zip_cmd = &s->zip_cmd;
	union zip_zres_s *result_ptr = &s->result;
	u32 queue;

	/* Prepares zip command based on the input parameters */
	prepare_zip_command(zip_ops, s, zip_cmd);

	atomic64_add(zip_ops->input_len, &zip_dev->stats.comp_in_bytes);
	/* Loads zip command into command queues and rings door bell */
	queue = zip_load_instr(zip_cmd, zip_dev);

	/* Stats update for compression requests submitted */
	atomic64_inc(&zip_dev->stats.comp_req_submit);

	/* Wait for completion or error */
	zip_poll_result(result_ptr);

	/* Stats update for compression requests completed */
	atomic64_inc(&zip_dev->stats.comp_req_complete);

	zip_ops->compcode = result_ptr->s.compcode;
	switch (zip_ops->compcode) {
	case ZIP_CMD_NOTDONE:
		zip_dbg("Zip instruction not yet completed");
		return ZIP_ERROR;

	case ZIP_CMD_SUCCESS:
		zip_dbg("Zip instruction completed successfully");
		zip_update_cmd_bufs(zip_dev, queue);
		break;

	case ZIP_CMD_DTRUNC:
		zip_dbg("Output Truncate error");
		/* Returning ZIP_ERROR to avoid copy to user */
		return ZIP_ERROR;

	default:
		zip_err("Zip instruction failed. Code:%d", zip_ops->compcode);
		return ZIP_ERROR;
	}

	/* Update the CRC depending on the format */
	switch (zip_ops->format) {
	case RAW_FORMAT:
		zip_dbg("RAW Format: %d ", zip_ops->format);
		/* Get checksum from engine, need to feed it again */
		zip_ops->csum = result_ptr->s.adler32;
		break;

	case ZLIB_FORMAT:
		zip_dbg("ZLIB Format: %d ", zip_ops->format);
		zip_ops->csum = result_ptr->s.adler32;
		break;

	case GZIP_FORMAT:
		zip_dbg("GZIP Format: %d ", zip_ops->format);
		zip_ops->csum = result_ptr->s.crc32;
		break;

	case LZS_FORMAT:
		zip_dbg("LZS Format: %d ", zip_ops->format);
		break;

	default:
		zip_err("Unknown Format:%d\n", zip_ops->format);
	}

	atomic64_add(result_ptr->s.totalbyteswritten,
		     &zip_dev->stats.comp_out_bytes);

	/* Update output_len */
	if (zip_ops->output_len < result_ptr->s.totalbyteswritten) {
		/* Dynamic stop && strm->output_len < zipconstants[onfsize] */
		zip_err("output_len (%d) < total bytes written(%d)\n",
			zip_ops->output_len, result_ptr->s.totalbyteswritten);
		zip_ops->output_len = 0;

	} else {
		zip_ops->output_len = result_ptr->s.totalbyteswritten;
	}

	return 0;
}