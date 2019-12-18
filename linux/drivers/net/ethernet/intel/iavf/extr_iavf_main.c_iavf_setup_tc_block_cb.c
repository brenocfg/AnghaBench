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
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 128 
 int iavf_setup_tc_cls_flower (void*,void*) ; 

__attribute__((used)) static int iavf_setup_tc_block_cb(enum tc_setup_type type, void *type_data,
				  void *cb_priv)
{
	switch (type) {
	case TC_SETUP_CLSFLOWER:
		return iavf_setup_tc_cls_flower(cb_priv, type_data);
	default:
		return -EOPNOTSUPP;
	}
}