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
struct sky2_port {int tx_pending; } ;

/* Variables and functions */
 int tx_inuse (struct sky2_port const*) ; 

__attribute__((used)) static inline int tx_avail(const struct sky2_port *sky2)
{
	return sky2->tx_pending - tx_inuse(sky2);
}