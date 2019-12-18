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
struct lpuart_port {scalar_t__ devtype; } ;

/* Variables and functions */
 scalar_t__ IMX8QXP_LPUART ; 

__attribute__((used)) static inline bool is_imx8qxp_lpuart(struct lpuart_port *sport)
{
	return sport->devtype == IMX8QXP_LPUART;
}