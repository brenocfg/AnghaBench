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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {int /*<<< orphan*/  std; } ;

/* Variables and functions */

__attribute__((used)) static int bttv_g_std(struct file *file, void *priv, v4l2_std_id *id)
{
	struct bttv_fh *fh  = priv;
	struct bttv *btv = fh->btv;

	*id = btv->std;
	return 0;
}