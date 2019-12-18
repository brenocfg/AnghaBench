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
struct usbhs_priv {int dummy; } ;
struct usbhs_fifo {int /*<<< orphan*/  ctr; } ;

/* Variables and functions */
 int EBUSY ; 
 int FRDY ; 
 int usbhs_read (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsf_fifo_barrier(struct usbhs_priv *priv,
			       struct usbhs_fifo *fifo)
{
	/* The FIFO port is accessible */
	if (usbhs_read(priv, fifo->ctr) & FRDY)
		return 0;

	return -EBUSY;
}