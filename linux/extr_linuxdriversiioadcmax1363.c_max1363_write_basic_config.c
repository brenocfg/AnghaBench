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
typedef  int /*<<< orphan*/  u8 ;
struct max1363_state {int (* send ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  client; int /*<<< orphan*/  configbyte; int /*<<< orphan*/  setupbyte; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int max1363_write_basic_config(struct max1363_state *st)
{
	u8 tx_buf[2] = { st->setupbyte, st->configbyte };

	return st->send(st->client, tx_buf, 2);
}