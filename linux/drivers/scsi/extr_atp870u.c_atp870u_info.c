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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static const char *atp870u_info(struct Scsi_Host *notused)
{
	static char buffer[128];

	strcpy(buffer, "ACARD AEC-6710/6712/67160 PCI Ultra/W/LVD SCSI-3 Adapter Driver V2.6+ac ");

	return buffer;
}