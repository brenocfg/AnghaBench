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
typedef  int /*<<< orphan*/  ushort ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  int /*<<< orphan*/  ASCEEP_CONFIG ;

/* Variables and functions */
 int ASC_EEP_MAX_RETRY ; 
 int AscSetEEPConfigOnce (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AscSetEEPConfig(PortAddr iop_base, ASCEEP_CONFIG *cfg_buf,
			   ushort bus_type)
{
	int retry;
	int n_error;

	retry = 0;
	while (true) {
		if ((n_error = AscSetEEPConfigOnce(iop_base, cfg_buf,
						   bus_type)) == 0) {
			break;
		}
		if (++retry > ASC_EEP_MAX_RETRY) {
			break;
		}
	}
	return n_error;
}