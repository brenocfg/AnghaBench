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
struct usbnet {unsigned long* data; } ;
struct sierra_net_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void sierra_net_set_private(struct usbnet *dev,
			struct sierra_net_data *priv)
{
	dev->data[0] = (unsigned long)priv;
}