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
typedef  enum guc_log_buffer_type { ____Placeholder_guc_log_buffer_type } guc_log_buffer_type ;

/* Variables and functions */
 unsigned int CRASH_BUFFER_SIZE ; 
 unsigned int DPC_BUFFER_SIZE ; 
#define  GUC_CRASH_DUMP_LOG_BUFFER 130 
#define  GUC_DPC_LOG_BUFFER 129 
#define  GUC_ISR_LOG_BUFFER 128 
 unsigned int ISR_BUFFER_SIZE ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static unsigned int guc_get_log_buffer_size(enum guc_log_buffer_type type)
{
	switch (type) {
	case GUC_ISR_LOG_BUFFER:
		return ISR_BUFFER_SIZE;
	case GUC_DPC_LOG_BUFFER:
		return DPC_BUFFER_SIZE;
	case GUC_CRASH_DUMP_LOG_BUFFER:
		return CRASH_BUFFER_SIZE;
	default:
		MISSING_CASE(type);
	}

	return 0;
}