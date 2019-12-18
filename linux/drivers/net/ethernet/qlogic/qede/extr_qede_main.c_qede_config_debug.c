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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  QED_LEVEL_INFO ; 
 int /*<<< orphan*/  QED_LEVEL_NOTICE ; 
 int /*<<< orphan*/  QED_LEVEL_VERBOSE ; 
 int QED_LOG_INFO_MASK ; 
 int QED_LOG_NOTICE_MASK ; 
 int QED_LOG_VERBOSE_MASK ; 

void qede_config_debug(uint debug, u32 *p_dp_module, u8 *p_dp_level)
{
	*p_dp_level = QED_LEVEL_NOTICE;
	*p_dp_module = 0;

	if (debug & QED_LOG_VERBOSE_MASK) {
		*p_dp_level = QED_LEVEL_VERBOSE;
		*p_dp_module = (debug & 0x3FFFFFFF);
	} else if (debug & QED_LOG_INFO_MASK) {
		*p_dp_level = QED_LEVEL_INFO;
	} else if (debug & QED_LOG_NOTICE_MASK) {
		*p_dp_level = QED_LEVEL_NOTICE;
	}
}