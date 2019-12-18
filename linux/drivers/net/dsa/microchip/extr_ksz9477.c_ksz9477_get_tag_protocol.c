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
struct ksz_device {int features; } ;
struct dsa_switch {struct ksz_device* priv; } ;
typedef  enum dsa_tag_protocol { ____Placeholder_dsa_tag_protocol } dsa_tag_protocol ;

/* Variables and functions */
 int DSA_TAG_PROTO_KSZ9477 ; 
 int DSA_TAG_PROTO_KSZ9893 ; 
 int IS_9893 ; 

__attribute__((used)) static enum dsa_tag_protocol ksz9477_get_tag_protocol(struct dsa_switch *ds,
						      int port)
{
	enum dsa_tag_protocol proto = DSA_TAG_PROTO_KSZ9477;
	struct ksz_device *dev = ds->priv;

	if (dev->features & IS_9893)
		proto = DSA_TAG_PROTO_KSZ9893;
	return proto;
}