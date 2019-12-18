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
struct scsi_cmnd {int* cmnd; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int srb10_len(const struct scsi_cmnd *cmd)
{
	return cmd->cmnd[7] << 8 | cmd->cmnd[8];
}