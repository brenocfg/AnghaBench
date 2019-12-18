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
struct ubi_vid_io_buf {int dummy; } ;
struct ubi_device {int /*<<< orphan*/  vid_hdr_alsize; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ubi_vid_io_buf*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ubi_vid_io_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_init_vid_buf (struct ubi_device const*,struct ubi_vid_io_buf*,void*) ; 

__attribute__((used)) static inline struct ubi_vid_io_buf *
ubi_alloc_vid_buf(const struct ubi_device *ubi, gfp_t gfp_flags)
{
	struct ubi_vid_io_buf *vidb;
	void *buf;

	vidb = kzalloc(sizeof(*vidb), gfp_flags);
	if (!vidb)
		return NULL;

	buf = kmalloc(ubi->vid_hdr_alsize, gfp_flags);
	if (!buf) {
		kfree(vidb);
		return NULL;
	}

	ubi_init_vid_buf(ubi, vidb, buf);

	return vidb;
}