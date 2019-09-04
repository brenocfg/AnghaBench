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
struct scif_endpt {int /*<<< orphan*/  remote_dev; } ;

/* Variables and functions */
 int _scifdev_alive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int scifdev_alive(struct scif_endpt *ep)
{
	return _scifdev_alive(ep->remote_dev);
}