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
struct iss_device {int /*<<< orphan*/  media_dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  csi2b; int /*<<< orphan*/  csi2a; int /*<<< orphan*/  ipipeif; int /*<<< orphan*/  ipipe; int /*<<< orphan*/  resizer; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap4iss_csi2_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap4iss_ipipe_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap4iss_ipipeif_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap4iss_resizer_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iss_unregister_entities(struct iss_device *iss)
{
	omap4iss_resizer_unregister_entities(&iss->resizer);
	omap4iss_ipipe_unregister_entities(&iss->ipipe);
	omap4iss_ipipeif_unregister_entities(&iss->ipipeif);
	omap4iss_csi2_unregister_entities(&iss->csi2a);
	omap4iss_csi2_unregister_entities(&iss->csi2b);

	v4l2_device_unregister(&iss->v4l2_dev);
	media_device_unregister(&iss->media_dev);
}