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
typedef  int /*<<< orphan*/  ws_d ;
struct writeset_disk {int /*<<< orphan*/  root; } ;
struct era_metadata {int /*<<< orphan*/  tm; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  dm_tm_inc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct writeset_disk*,void const*,int) ; 

__attribute__((used)) static void ws_inc(void *context, const void *value)
{
	struct era_metadata *md = context;
	struct writeset_disk ws_d;
	dm_block_t b;

	memcpy(&ws_d, value, sizeof(ws_d));
	b = le64_to_cpu(ws_d.root);

	dm_tm_inc(md->tm, b);
}