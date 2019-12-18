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

/* Variables and functions */
 int /*<<< orphan*/  DBF_ERR ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  qdio_dbf_error ; 

__attribute__((used)) static inline void DBF_ERROR_HEX(void *addr, int len)
{
	debug_event(qdio_dbf_error, DBF_ERR, addr, len);
}