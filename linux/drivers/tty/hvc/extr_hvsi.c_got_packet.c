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
typedef  int /*<<< orphan*/  uint8_t ;
struct hvsi_struct {int /*<<< orphan*/ * inbuf_end; } ;
struct hvsi_header {int dummy; } ;

/* Variables and functions */
 int len_packet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int got_packet(const struct hvsi_struct *hp, uint8_t *packet)
{
	if (hp->inbuf_end < packet + sizeof(struct hvsi_header))
		return 0; /* don't even have the packet header */

	if (hp->inbuf_end < (packet + len_packet(packet)))
		return 0; /* don't have the rest of the packet */

	return 1;
}