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
struct htc_target {struct htc_target* dev; } ;
struct htc_packet {struct htc_packet* dev; } ;

/* Variables and functions */
 struct htc_target* alloc_htc_packet_container (struct htc_target*) ; 
 int /*<<< orphan*/  kfree (struct htc_target*) ; 

__attribute__((used)) static void ath6kl_htc_pipe_cleanup(struct htc_target *target)
{
	struct htc_packet *packet;

	while (true) {
		packet = alloc_htc_packet_container(target);
		if (packet == NULL)
			break;
		kfree(packet);
	}

	kfree(target->dev);

	/* kfree our instance */
	kfree(target);
}