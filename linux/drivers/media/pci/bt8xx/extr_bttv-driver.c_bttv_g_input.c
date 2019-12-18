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
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {unsigned int input; } ;

/* Variables and functions */

__attribute__((used)) static int bttv_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	*i = btv->input;

	return 0;
}