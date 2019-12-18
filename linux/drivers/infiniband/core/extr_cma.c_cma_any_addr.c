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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 scalar_t__ cma_loopback_addr (struct sockaddr const*) ; 
 scalar_t__ cma_zero_addr (struct sockaddr const*) ; 

__attribute__((used)) static inline bool cma_any_addr(const struct sockaddr *addr)
{
	return cma_zero_addr(addr) || cma_loopback_addr(addr);
}