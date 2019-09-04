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
struct pxa_device_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pxa_device_desc pxa910_device_uart1 ; 
 struct pxa_device_desc pxa910_device_uart2 ; 
 int pxa_register_device (struct pxa_device_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pxa910_add_uart(int id)
{
	struct pxa_device_desc *d = NULL;

	switch (id) {
	case 1: d = &pxa910_device_uart1; break;
	case 2: d = &pxa910_device_uart2; break;
	}

	if (d == NULL)
		return -EINVAL;

	return pxa_register_device(d, NULL, 0);
}