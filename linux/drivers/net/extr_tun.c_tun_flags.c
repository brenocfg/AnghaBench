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
struct tun_struct {int flags; } ;

/* Variables and functions */
 int IFF_PERSIST ; 
 int IFF_TAP ; 
 int IFF_TUN ; 
 int TUN_FEATURES ; 

__attribute__((used)) static int tun_flags(struct tun_struct *tun)
{
	return tun->flags & (TUN_FEATURES | IFF_PERSIST | IFF_TUN | IFF_TAP);
}