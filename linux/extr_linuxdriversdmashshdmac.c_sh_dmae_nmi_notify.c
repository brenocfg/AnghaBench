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
struct sh_dmae_device {int dummy; } ;

/* Variables and functions */
 int DMAOR_NMIF ; 
 int dmaor_read (struct sh_dmae_device*) ; 
 int sh_dmae_reset (struct sh_dmae_device*) ; 

__attribute__((used)) static bool sh_dmae_nmi_notify(struct sh_dmae_device *shdev)
{
	/* Fast path out if NMIF is not asserted for this controller */
	if ((dmaor_read(shdev) & DMAOR_NMIF) == 0)
		return false;

	return sh_dmae_reset(shdev);
}