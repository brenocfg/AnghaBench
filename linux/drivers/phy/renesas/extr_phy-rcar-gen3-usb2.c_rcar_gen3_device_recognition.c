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
struct rcar_gen3_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcar_gen3_check_id (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  rcar_gen3_init_for_host (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  rcar_gen3_init_for_peri (struct rcar_gen3_chan*) ; 

__attribute__((used)) static void rcar_gen3_device_recognition(struct rcar_gen3_chan *ch)
{
	if (!rcar_gen3_check_id(ch))
		rcar_gen3_init_for_host(ch);
	else
		rcar_gen3_init_for_peri(ch);
}