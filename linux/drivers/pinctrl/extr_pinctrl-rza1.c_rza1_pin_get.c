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
struct rza1_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RZA1_PPR_REG ; 
 int rza1_get_bit (struct rza1_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int rza1_pin_get(struct rza1_port *port, unsigned int pin)
{
	return rza1_get_bit(port, RZA1_PPR_REG, pin);
}