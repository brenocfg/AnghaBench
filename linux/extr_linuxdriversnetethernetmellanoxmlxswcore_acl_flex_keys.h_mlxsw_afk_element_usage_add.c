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
struct mlxsw_afk_element_usage {int /*<<< orphan*/  usage; } ;
typedef  enum mlxsw_afk_element { ____Placeholder_mlxsw_afk_element } mlxsw_afk_element ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_afk_element_usage_add(struct mlxsw_afk_element_usage *elusage,
			    enum mlxsw_afk_element element)
{
	__set_bit(element, elusage->usage);
}