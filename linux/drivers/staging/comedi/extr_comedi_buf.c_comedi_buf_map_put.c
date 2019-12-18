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
struct comedi_buf_map {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_map_kref_release ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int comedi_buf_map_put(struct comedi_buf_map *bm)
{
	if (bm)
		return kref_put(&bm->refcount, comedi_buf_map_kref_release);
	return 1;
}