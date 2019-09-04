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

__attribute__((used)) static enum dsa_tag_protocol vsc73xx_get_tag_protocol(struct dsa_switch *ds,
						      int port)
{
	/* The switch internally uses a 8 byte header with length,
	 * source port, tag, LPA and priority. This is supposedly
	 * only accessible when operating the switch using the internal
	 * CPU or with an external CPU mapping the device in, but not
	 * when operating the switch over SPI and putting frames in/out
	 * on port 6 (the CPU port). So far we must assume that we
	 * cannot access the tag. (See "Internal frame header" section
	 * 3.9.1 in the manual.)
	 */
	return DSA_TAG_PROTO_NONE;
}