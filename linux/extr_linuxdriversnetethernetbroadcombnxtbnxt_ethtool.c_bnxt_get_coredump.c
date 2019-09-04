#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  time64_t ;
struct hwrm_ver_get_output {int dummy; } ;
struct coredump_segment_record {int /*<<< orphan*/  segment_id; int /*<<< orphan*/  component_id; } ;
struct bnxt_coredump_segment_hdr {int dummy; } ;
struct bnxt_coredump_record {int dummy; } ;
struct bnxt_coredump {int total_segs; scalar_t__ data; int /*<<< orphan*/ * member_0; } ;
struct bnxt {int /*<<< orphan*/  dev; struct bnxt_coredump_segment_hdr ver_resp; } ;
typedef  int /*<<< orphan*/  seg_hdr ;
struct TYPE_2__ {int tz_minuteswest; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_fill_coredump_record (struct bnxt*,void*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  bnxt_fill_coredump_seg_hdr (struct bnxt*,struct bnxt_coredump_segment_hdr*,struct coredump_segment_record*,int,int,int,int /*<<< orphan*/ ) ; 
 int bnxt_hwrm_dbg_coredump_initiate (struct bnxt*,int,int) ; 
 int bnxt_hwrm_dbg_coredump_list (struct bnxt*,struct bnxt_coredump*) ; 
 int bnxt_hwrm_dbg_coredump_retrieve (struct bnxt*,int,int,int*,void*,int) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,struct bnxt_coredump_segment_hdr*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ sys_tz ; 

__attribute__((used)) static int bnxt_get_coredump(struct bnxt *bp, void *buf, u32 *dump_len)
{
	u32 ver_get_resp_len = sizeof(struct hwrm_ver_get_output);
	struct coredump_segment_record *seg_record = NULL;
	u32 offset = 0, seg_hdr_len, seg_record_len;
	struct bnxt_coredump_segment_hdr seg_hdr;
	struct bnxt_coredump coredump = {NULL};
	time64_t start_time;
	u16 start_utc;
	int rc = 0, i;

	start_time = ktime_get_real_seconds();
	start_utc = sys_tz.tz_minuteswest * 60;
	seg_hdr_len = sizeof(seg_hdr);

	/* First segment should be hwrm_ver_get response */
	*dump_len = seg_hdr_len + ver_get_resp_len;
	if (buf) {
		bnxt_fill_coredump_seg_hdr(bp, &seg_hdr, NULL, ver_get_resp_len,
					   0, 0, 0);
		memcpy(buf + offset, &seg_hdr, seg_hdr_len);
		offset += seg_hdr_len;
		memcpy(buf + offset, &bp->ver_resp, ver_get_resp_len);
		offset += ver_get_resp_len;
	}

	rc = bnxt_hwrm_dbg_coredump_list(bp, &coredump);
	if (rc) {
		netdev_err(bp->dev, "Failed to get coredump segment list\n");
		goto err;
	}

	*dump_len += seg_hdr_len * coredump.total_segs;

	seg_record = (struct coredump_segment_record *)coredump.data;
	seg_record_len = sizeof(*seg_record);

	for (i = 0; i < coredump.total_segs; i++) {
		u16 comp_id = le16_to_cpu(seg_record->component_id);
		u16 seg_id = le16_to_cpu(seg_record->segment_id);
		u32 duration = 0, seg_len = 0;
		unsigned long start, end;

		start = jiffies;

		rc = bnxt_hwrm_dbg_coredump_initiate(bp, comp_id, seg_id);
		if (rc) {
			netdev_err(bp->dev,
				   "Failed to initiate coredump for seg = %d\n",
				   seg_record->segment_id);
			goto next_seg;
		}

		/* Write segment data into the buffer */
		rc = bnxt_hwrm_dbg_coredump_retrieve(bp, comp_id, seg_id,
						     &seg_len, buf,
						     offset + seg_hdr_len);
		if (rc)
			netdev_err(bp->dev,
				   "Failed to retrieve coredump for seg = %d\n",
				   seg_record->segment_id);

next_seg:
		end = jiffies;
		duration = jiffies_to_msecs(end - start);
		bnxt_fill_coredump_seg_hdr(bp, &seg_hdr, seg_record, seg_len,
					   rc, duration, 0);

		if (buf) {
			/* Write segment header into the buffer */
			memcpy(buf + offset, &seg_hdr, seg_hdr_len);
			offset += seg_hdr_len + seg_len;
		}

		*dump_len += seg_len;
		seg_record =
			(struct coredump_segment_record *)((u8 *)seg_record +
							   seg_record_len);
	}

err:
	if (buf)
		bnxt_fill_coredump_record(bp, buf + offset, start_time,
					  start_utc, coredump.total_segs + 1,
					  rc);
	kfree(coredump.data);
	*dump_len += sizeof(struct bnxt_coredump_record);

	return rc;
}