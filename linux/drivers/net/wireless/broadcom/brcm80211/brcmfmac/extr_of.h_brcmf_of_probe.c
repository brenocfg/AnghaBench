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
struct device {int dummy; } ;
struct brcmf_mp_device {int dummy; } ;
typedef  enum brcmf_bus_type { ____Placeholder_brcmf_bus_type } brcmf_bus_type ;

/* Variables and functions */

__attribute__((used)) static void brcmf_of_probe(struct device *dev, enum brcmf_bus_type bus_type,
			   struct brcmf_mp_device *settings)
{
}