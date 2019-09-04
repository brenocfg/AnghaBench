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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxcpld_i2c_priv {int base_addr; } ;

/* Variables and functions */
 int inb (int) ; 
 int inl (int) ; 
 int /*<<< orphan*/  inw (int) ; 
 int /*<<< orphan*/  mlxcpld_i2c_lpc_read_buf (int*,int,int) ; 

__attribute__((used)) static void mlxcpld_i2c_read_comm(struct mlxcpld_i2c_priv *priv, u8 offs,
				  u8 *data, u8 datalen)
{
	u32 addr = priv->base_addr + offs;

	switch (datalen) {
	case 1:
		*(data) = inb(addr);
		break;
	case 2:
		*((u16 *)data) = inw(addr);
		break;
	case 3:
		*((u16 *)data) = inw(addr);
		*(data + 2) = inb(addr + 2);
		break;
	case 4:
		*((u32 *)data) = inl(addr);
		break;
	default:
		mlxcpld_i2c_lpc_read_buf(data, datalen, addr);
		break;
	}
}