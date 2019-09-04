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
struct nbpf_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBPF_CHAN_CTRL ; 
 int /*<<< orphan*/  NBPF_CHAN_CTRL_CLREN ; 
 int /*<<< orphan*/  nbpf_chan_write (struct nbpf_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbpf_chan_halt(struct nbpf_channel *chan)
{
	nbpf_chan_write(chan, NBPF_CHAN_CTRL, NBPF_CHAN_CTRL_CLREN);
}