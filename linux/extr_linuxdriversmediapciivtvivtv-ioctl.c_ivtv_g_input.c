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
struct ivtv {unsigned int active_input; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct ivtv* itv; } ;

/* Variables and functions */
 TYPE_1__* fh2id (void*) ; 

__attribute__((used)) static int ivtv_g_input(struct file *file, void *fh, unsigned int *i)
{
	struct ivtv *itv = fh2id(fh)->itv;

	*i = itv->active_input;

	return 0;
}