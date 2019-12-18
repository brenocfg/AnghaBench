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
struct TYPE_2__ {scalar_t__ eof; } ;
struct ctl_pkg {TYPE_1__ frame; } ;
struct cfg_error_pkg {int error; } ;

/* Variables and functions */
#define  TB_CFG_ERROR_FLOW_CONTROL_ERROR 130 
#define  TB_CFG_ERROR_HEC_ERROR_DETECTED 129 
#define  TB_CFG_ERROR_LINK_ERROR 128 
 scalar_t__ TB_CFG_PKG_ERROR ; 

__attribute__((used)) static int tb_async_error(const struct ctl_pkg *pkg)
{
	const struct cfg_error_pkg *error = (const struct cfg_error_pkg *)pkg;

	if (pkg->frame.eof != TB_CFG_PKG_ERROR)
		return false;

	switch (error->error) {
	case TB_CFG_ERROR_LINK_ERROR:
	case TB_CFG_ERROR_HEC_ERROR_DETECTED:
	case TB_CFG_ERROR_FLOW_CONTROL_ERROR:
		return true;

	default:
		return false;
	}
}