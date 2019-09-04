#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ubi_vid_io_buf {void* hdr; void* buffer; } ;
struct ubi_device {int vid_hdr_shift; int /*<<< orphan*/  vid_hdr_alsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ubi_init_vid_buf(const struct ubi_device *ubi,
				    struct ubi_vid_io_buf *vidb,
				    void *buf)
{
	if (buf)
		memset(buf, 0, ubi->vid_hdr_alsize);

	vidb->buffer = buf;
	vidb->hdr = buf + ubi->vid_hdr_shift;
}