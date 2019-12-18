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
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {scalar_t__ chip_id; } ;
typedef  enum dsa_tag_protocol { ____Placeholder_dsa_tag_protocol } dsa_tag_protocol ;

/* Variables and functions */
 int B53_CPU_PORT ; 
 scalar_t__ BCM58XX_DEVICE_ID ; 
 int DSA_TAG_PROTO_BRCM ; 
 int DSA_TAG_PROTO_BRCM_PREPEND ; 
 int DSA_TAG_PROTO_NONE ; 
 int /*<<< orphan*/  b53_can_enable_brcm_tags (struct dsa_switch*,int) ; 
 scalar_t__ is531x5 (struct b53_device*) ; 
 scalar_t__ is5325 (struct b53_device*) ; 
 scalar_t__ is5365 (struct b53_device*) ; 
 scalar_t__ is539x (struct b53_device*) ; 

enum dsa_tag_protocol b53_get_tag_protocol(struct dsa_switch *ds, int port)
{
	struct b53_device *dev = ds->priv;

	/* Older models (5325, 5365) support a different tag format that we do
	 * not support in net/dsa/tag_brcm.c yet. 539x and 531x5 require managed
	 * mode to be turned on which means we need to specifically manage ARL
	 * misses on multicast addresses (TBD).
	 */
	if (is5325(dev) || is5365(dev) || is539x(dev) || is531x5(dev) ||
	    !b53_can_enable_brcm_tags(ds, port))
		return DSA_TAG_PROTO_NONE;

	/* Broadcom BCM58xx chips have a flow accelerator on Port 8
	 * which requires us to use the prepended Broadcom tag type
	 */
	if (dev->chip_id == BCM58XX_DEVICE_ID && port == B53_CPU_PORT)
		return DSA_TAG_PROTO_BRCM_PREPEND;

	return DSA_TAG_PROTO_BRCM;
}