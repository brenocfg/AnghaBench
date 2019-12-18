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
struct TYPE_2__ {scalar_t__ magic; int version; scalar_t__ nr_regions; } ;
struct log_c {scalar_t__ sync; TYPE_1__ header; int /*<<< orphan*/  disk_header; } ;

/* Variables and functions */
 scalar_t__ DEFAULTSYNC ; 
 int /*<<< orphan*/  DMWARN (char*) ; 
 int EINVAL ; 
 int MIRROR_DISK_VERSION ; 
 scalar_t__ MIRROR_MAGIC ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  header_from_disk (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int rw_header (struct log_c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_header(struct log_c *log)
{
	int r;

	r = rw_header(log, REQ_OP_READ);
	if (r)
		return r;

	header_from_disk(&log->header, log->disk_header);

	/* New log required? */
	if (log->sync != DEFAULTSYNC || log->header.magic != MIRROR_MAGIC) {
		log->header.magic = MIRROR_MAGIC;
		log->header.version = MIRROR_DISK_VERSION;
		log->header.nr_regions = 0;
	}

#ifdef __LITTLE_ENDIAN
	if (log->header.version == 1)
		log->header.version = 2;
#endif

	if (log->header.version != MIRROR_DISK_VERSION) {
		DMWARN("incompatible disk log version");
		return -EINVAL;
	}

	return 0;
}