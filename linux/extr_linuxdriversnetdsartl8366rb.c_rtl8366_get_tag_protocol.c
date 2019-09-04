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
struct dsa_switch {int dummy; } ;
typedef  enum dsa_tag_protocol { ____Placeholder_dsa_tag_protocol } dsa_tag_protocol ;

/* Variables and functions */
 int DSA_TAG_PROTO_NONE ; 

__attribute__((used)) static enum dsa_tag_protocol rtl8366_get_tag_protocol(struct dsa_switch *ds,
						      int port)
{
	/* For now, the RTL switches are handled without any custom tags.
	 *
	 * It is possible to turn on "custom tags" by removing the
	 * RTL8368RB_CPU_INSTAG flag when enabling the port but what it
	 * does is unfamiliar to DSA: ethernet frames of type 8899, the Realtek
	 * Remote Control Protocol (RRCP) start to appear on the CPU port of
	 * the device. So this is not the ordinary few extra bytes in the
	 * frame. Instead it appears that the switch starts to talk Realtek
	 * RRCP internally which means a pretty complex RRCP implementation
	 * decoding and responding the RRCP protocol is needed to exploit this.
	 *
	 * The OpenRRCP project (dormant since 2009) have reverse-egineered
	 * parts of the protocol.
	 */
	return DSA_TAG_PROTO_NONE;
}