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
struct usbnet {int /*<<< orphan*/  data; } ;
struct mcs7830_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mcs7830_data *mcs7830_get_data(struct usbnet *dev)
{
	return (struct mcs7830_data *)&dev->data;
}