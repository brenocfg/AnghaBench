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
struct idma64_chan {int /*<<< orphan*/  mask; } ;
struct idma64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_EN ; 
 int /*<<< orphan*/  channel_clear_bit (struct idma64*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idma64_chan_stop(struct idma64 *idma64, struct idma64_chan *idma64c)
{
	channel_clear_bit(idma64, CH_EN, idma64c->mask);
}