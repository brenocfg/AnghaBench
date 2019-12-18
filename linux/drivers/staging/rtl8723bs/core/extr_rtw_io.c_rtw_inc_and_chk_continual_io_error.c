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
struct dvobj_priv {int /*<<< orphan*/  continual_io_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,struct dvobj_priv*,int,int) ; 
 int MAX_CONTINUAL_IO_ERR ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

int rtw_inc_and_chk_continual_io_error(struct dvobj_priv *dvobj)
{
	int ret = false;
	int value = atomic_inc_return(&dvobj->continual_io_error);
	if (value > MAX_CONTINUAL_IO_ERR) {
		DBG_871X("[dvobj:%p][ERROR] continual_io_error:%d > %d\n", dvobj, value, MAX_CONTINUAL_IO_ERR);
		ret = true;
	} else {
		/* DBG_871X("[dvobj:%p] continual_io_error:%d\n", dvobj, value); */
	}
	return ret;
}