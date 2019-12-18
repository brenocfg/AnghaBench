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
struct usba_udc {int dummy; } ;
struct usba_ep {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void usba_ep_init_debugfs(struct usba_udc *udc,
					 struct usba_ep *ep)
{

}