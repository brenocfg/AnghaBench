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
struct hsc_client_data {scalar_t__ usecnt; int /*<<< orphan*/  cl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  hsi_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_release_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __hsc_port_release(struct hsc_client_data *cl_data)
{
	BUG_ON(cl_data->usecnt == 0);

	if (--cl_data->usecnt == 0) {
		hsi_flush(cl_data->cl);
		hsi_release_port(cl_data->cl);
	}
}