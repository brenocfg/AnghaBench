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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int FM93C56A_DATA_BITS_16 ; 

__attribute__((used)) static inline int eeprom_no_data_bits(struct scsi_qla_host *ha)
{
	return FM93C56A_DATA_BITS_16;
}