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
typedef  unsigned int u32 ;
struct tdfx_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DACADDR ; 
 int /*<<< orphan*/  DACDATA ; 
 int /*<<< orphan*/  banshee_make_room (struct tdfx_par*,int) ; 
 int /*<<< orphan*/  tdfx_inl (struct tdfx_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdfx_outl (struct tdfx_par*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void do_setpalentry(struct tdfx_par *par, unsigned regno, u32 c)
{
	banshee_make_room(par, 2);
	tdfx_outl(par, DACADDR, regno);
	/* read after write makes it working */
	tdfx_inl(par, DACADDR);
	tdfx_outl(par, DACDATA, c);
}