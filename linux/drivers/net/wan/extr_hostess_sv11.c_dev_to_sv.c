#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct z8530_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 

__attribute__((used)) static inline struct z8530_dev* dev_to_sv(struct net_device *dev)
{
	return (struct z8530_dev *)dev_to_hdlc(dev)->priv;
}