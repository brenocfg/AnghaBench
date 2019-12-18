#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct soc_pcmcia_socket {struct max1600* driver_data; scalar_t__ nr; TYPE_2__ socket; } ;
struct max1600 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX1600_CHAN_A ; 
 int /*<<< orphan*/  MAX1600_CHAN_B ; 
 int /*<<< orphan*/  MAX1600_CODE_HIGH ; 
 int max1600_init (int /*<<< orphan*/ ,struct max1600**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lubbock_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	struct max1600 *m;
	int ret;

	ret = max1600_init(skt->socket.dev.parent, &m,
			   skt->nr ? MAX1600_CHAN_B : MAX1600_CHAN_A,
			   MAX1600_CODE_HIGH);
	if (ret == 0)
		skt->driver_data = m;

	return ret;
}