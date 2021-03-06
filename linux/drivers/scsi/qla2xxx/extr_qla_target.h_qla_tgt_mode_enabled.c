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
struct scsi_qla_host {TYPE_1__* host; } ;
struct TYPE_2__ {scalar_t__ active_mode; } ;

/* Variables and functions */
 scalar_t__ MODE_TARGET ; 

__attribute__((used)) static inline bool qla_tgt_mode_enabled(struct scsi_qla_host *ha)
{
	return ha->host->active_mode == MODE_TARGET;
}