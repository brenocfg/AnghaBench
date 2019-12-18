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
struct tun_struct {TYPE_1__* dev; } ;
struct ifreq {int /*<<< orphan*/  ifr_flags; int /*<<< orphan*/  ifr_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_debug (int /*<<< orphan*/ ,struct tun_struct*,char*) ; 
 int /*<<< orphan*/  tun_flags (struct tun_struct*) ; 

__attribute__((used)) static void tun_get_iff(struct tun_struct *tun, struct ifreq *ifr)
{
	tun_debug(KERN_INFO, tun, "tun_get_iff\n");

	strcpy(ifr->ifr_name, tun->dev->name);

	ifr->ifr_flags = tun_flags(tun);

}