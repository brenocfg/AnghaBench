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
struct chtls_sock {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  chtls_sock_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __chtls_sock_put(const char *fn, struct chtls_sock *csk)
{
	kref_put(&csk->kref, chtls_sock_free);
}