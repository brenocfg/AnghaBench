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
typedef  int uint32_t ;

/* Variables and functions */
#define  QLA8XXX_DEV_COLD 134 
#define  QLA8XXX_DEV_FAILED 133 
#define  QLA8XXX_DEV_INITIALIZING 132 
#define  QLA8XXX_DEV_NEED_QUIESCENT 131 
#define  QLA8XXX_DEV_NEED_RESET 130 
#define  QLA8XXX_DEV_QUIESCENT 129 
#define  QLA8XXX_DEV_READY 128 

__attribute__((used)) static const char *
qla83xx_dev_state_to_string(uint32_t dev_state)
{
	switch (dev_state) {
	case QLA8XXX_DEV_COLD:
		return "COLD/RE-INIT";
	case QLA8XXX_DEV_INITIALIZING:
		return "INITIALIZING";
	case QLA8XXX_DEV_READY:
		return "READY";
	case QLA8XXX_DEV_NEED_RESET:
		return "NEED RESET";
	case QLA8XXX_DEV_NEED_QUIESCENT:
		return "NEED QUIESCENT";
	case QLA8XXX_DEV_FAILED:
		return "FAILED";
	case QLA8XXX_DEV_QUIESCENT:
		return "QUIESCENT";
	default:
		return "Unknown";
	}
}