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
struct tb_ctl {int dummy; } ;
struct tb_cfg_result {scalar_t__ tb_error; } ;
typedef  enum tb_cfg_space { ____Placeholder_tb_cfg_space } tb_cfg_space ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ TB_CFG_ERROR_INVALID_CONFIG_SPACE ; 
 int TB_CFG_PORT ; 
 int /*<<< orphan*/  tb_cfg_print_error (struct tb_ctl*,struct tb_cfg_result const*) ; 

__attribute__((used)) static int tb_cfg_get_error(struct tb_ctl *ctl, enum tb_cfg_space space,
			    const struct tb_cfg_result *res)
{
	/*
	 * For unimplemented ports access to port config space may return
	 * TB_CFG_ERROR_INVALID_CONFIG_SPACE (alternatively their type is
	 * set to TB_TYPE_INACTIVE). In the former case return -ENODEV so
	 * that the caller can mark the port as disabled.
	 */
	if (space == TB_CFG_PORT &&
	    res->tb_error == TB_CFG_ERROR_INVALID_CONFIG_SPACE)
		return -ENODEV;

	tb_cfg_print_error(ctl, res);
	return -EIO;
}