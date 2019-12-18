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
struct iss_ipipeif_device {int /*<<< orphan*/  wait; int /*<<< orphan*/  state; } ;
struct iss_device {struct iss_ipipeif_device ipipeif; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISS_PIPELINE_STREAM_STOPPED ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int ipipeif_init_entities (struct iss_ipipeif_device*) ; 

int omap4iss_ipipeif_init(struct iss_device *iss)
{
	struct iss_ipipeif_device *ipipeif = &iss->ipipeif;

	ipipeif->state = ISS_PIPELINE_STREAM_STOPPED;
	init_waitqueue_head(&ipipeif->wait);

	return ipipeif_init_entities(ipipeif);
}