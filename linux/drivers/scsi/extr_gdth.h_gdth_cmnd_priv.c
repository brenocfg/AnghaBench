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
struct scsi_cmnd {scalar_t__ host_scribble; } ;
struct gdth_cmndinfo {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct gdth_cmndinfo *gdth_cmnd_priv(struct scsi_cmnd* cmd)
{
	return (struct gdth_cmndinfo *)cmd->host_scribble;
}