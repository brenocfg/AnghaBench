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
struct ubi_vid_io_buf {struct ubi_vid_io_buf* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ubi_vid_io_buf*) ; 

__attribute__((used)) static inline void ubi_free_vid_buf(struct ubi_vid_io_buf *vidb)
{
	if (!vidb)
		return;

	kfree(vidb->buffer);
	kfree(vidb);
}