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
typedef  int /*<<< orphan*/  u16 ;
struct td {int dummy; } ;
struct ohci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hc16_to_cpup (struct ohci_hcd const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_hwPSWp (struct ohci_hcd const*,struct td const*,int) ; 

__attribute__((used)) static inline u16 ohci_hwPSW(const struct ohci_hcd *ohci,
                               const struct td *td, int index)
{
	return hc16_to_cpup(ohci, ohci_hwPSWp(ohci, td, index));
}