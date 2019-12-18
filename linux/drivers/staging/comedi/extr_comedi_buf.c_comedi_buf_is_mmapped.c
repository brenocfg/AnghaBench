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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_buf_map {int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {struct comedi_buf_map* buf_map; } ;

/* Variables and functions */
 int kref_read (int /*<<< orphan*/ *) ; 

bool comedi_buf_is_mmapped(struct comedi_subdevice *s)
{
	struct comedi_buf_map *bm = s->async->buf_map;

	return bm && (kref_read(&bm->refcount) > 1);
}