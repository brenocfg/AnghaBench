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
typedef  enum ath10k_scan_state { ____Placeholder_ath10k_scan_state } ath10k_scan_state ;

/* Variables and functions */
#define  ATH10K_SCAN_ABORTING 131 
#define  ATH10K_SCAN_IDLE 130 
#define  ATH10K_SCAN_RUNNING 129 
#define  ATH10K_SCAN_STARTING 128 

__attribute__((used)) static inline const char *ath10k_scan_state_str(enum ath10k_scan_state state)
{
	switch (state) {
	case ATH10K_SCAN_IDLE:
		return "idle";
	case ATH10K_SCAN_STARTING:
		return "starting";
	case ATH10K_SCAN_RUNNING:
		return "running";
	case ATH10K_SCAN_ABORTING:
		return "aborting";
	}

	return "unknown";
}