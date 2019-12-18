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
struct ks_wlan_private {int dummy; } ;
typedef  enum mib_attribute { ____Placeholder_mib_attribute } mib_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  MIB_VALUE_TYPE_OSTRING ; 
 int /*<<< orphan*/  hostif_mib_set_request (struct ks_wlan_private*,int,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static inline void hostif_mib_set_request_ostring(struct ks_wlan_private *priv,
						  enum mib_attribute attr,
						  void *data, size_t size)
{
	hostif_mib_set_request(priv, attr, MIB_VALUE_TYPE_OSTRING, data, size);
}